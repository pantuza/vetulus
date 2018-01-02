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
#include <sys/stat.h>

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>


using std::cout;
using std::endl;
using std::string;

using google::protobuf::compiler::Importer;
using google::protobuf::compiler::DiskSourceTree;
using google::protobuf::compiler::MultiFileErrorCollector;
using google::protobuf::compiler::GeneratorContext;
using google::protobuf::compiler::cpp::CppGenerator;
using google::protobuf::FileDescriptor;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::FileOutputStream;




class ErrorCollector : public MultiFileErrorCollector
{
  public:
    explicit ErrorCollector() {}
    void AddError(const string & filename, int line, int column,
                  const string & message)
    {
        cout << "file: " << filename << "\tmessage: " << message << endl << endl;
    }
};

class VetulusContextGenerator : public GeneratorContext
{
 public:
    ZeroCopyOutputStream* Open(const string & filename)
    {
        int outfd = open(filename, O_WRONLY);
        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;
    }
};


int
main(int argc, char* argv[])
{
    DiskSourceTree tree;
    tree.MapPath("vetulus", ".");
    ErrorCollector error_collector;
    Importer importer(&tree, &error_collector);
    const FileDescriptor* fd = importer.Import("vetulus/test.proto");
    cout << "fd: " << fd->name() << endl;

    VetulusContextGenerator context;
    context.Open("test.pb");

    CppGenerator generator;
    string error = "num compilô!";
    generator.Generate(fd, "", (GeneratorContext *) &context, &error);

    return EXIT_SUCCESS;
}
