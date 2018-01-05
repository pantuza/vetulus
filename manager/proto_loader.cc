/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  proto_loader.cc
 *
 *    Description:  Dinamically loads protobuffers files
 *
 *        Version:  1.0
 *        Created:  01/02/2018 12:47:30 AM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com),
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/compiler/plugin.pb.h>


using std::cout;
using std::endl;
using std::string;
using std::vector;

using google::protobuf::compiler::Importer;
using google::protobuf::compiler::DiskSourceTree;
using google::protobuf::compiler::MultiFileErrorCollector;
using google::protobuf::compiler::GeneratorContext;
using google::protobuf::compiler::cpp::CppGenerator;
using google::protobuf::compiler::Version;
using google::protobuf::FileDescriptor;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::FileOutputStream;




class ErrorCollector : public MultiFileErrorCollector
{
 public:
    ErrorCollector() {}
    void AddError(const string & filename, int line, int column,
                  const string & message)
    {
        cout << "file: " << filename << "\tmessage: " << message << endl;
    }
};


class VetulusContextGenerator : public GeneratorContext
{
 public:
    virtual ZeroCopyOutputStream* Open(const string & filename)
    {
        cout << "trying to open: " << filename << endl;

        int pos = filename.rfind("/");
        int outfd = open(filename.substr(pos + 1).c_str(), O_WRONLY | O_CREAT);

        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;
    }

    virtual ZeroCopyOutputStream* OpenForAppend(const string & filename)
    {
        int outfd = open(filename.c_str(), O_APPEND);
        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;
    }

    virtual ZeroCopyOutputStream* OpenForInsert(const string & filename,
                                        const string & insertion_point)
    {
        int outfd = open(filename.c_str(), O_WRONLY);
        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;

    }
    virtual void ListParsedFiles(vector< const FileDescriptor * > * output) {}
    virtual void GetCompilerVersion(Version * version) const {}
};


int
main(int argc, char* argv[])
{
    DiskSourceTree tree;
    tree.MapPath("vetulus", ".");
    ErrorCollector error_collector;
    Importer importer(&tree, &error_collector);
    const FileDescriptor* fd = importer.Import("vetulus/test.proto");
    cout << "Importing file: " << fd->name() << endl;

    VetulusContextGenerator context;

    CppGenerator generator;
    string error;
    if (generator.Generate(fd, "", &context, &error)) {
        cout << "Probably generated" << endl;
    } else {
        cerr << "Not generated: " << error << endl;
    }

    return EXIT_SUCCESS;
}
