/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  proto_loader.h
 *
 *    Description:  Header file of class that dinamically loads
 *                  protobuffers files and compiles its classes
 *
 *        Version:  1.0
 *        Created:  01/02/2018 09:43:22 AM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com),
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#ifndef _MANAGER_PROTO_LOADER_H
#define _MANAGER_PROTO_LOADER_H

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

#include "./spdlog/spdlog.h"


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
        spdlog::get("Proto Loader")->info(
                    "File: {0}\tmessage: {1}", filename, message);
    }
};



/*
 * The context generator that is used to compile protobuf files
 */
class VetulusContextGenerator : public GeneratorContext
{
 public:
    virtual ZeroCopyOutputStream* Open(const string & filename)
    {
        spdlog::get("Proto Loader")->info("Opening: {0}", filename);

        int pos = filename.rfind("/");
        int outfd = open(filename.substr(pos + 1).c_str(), O_WRONLY | O_CREAT);

        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;
    }

    virtual ZeroCopyOutputStream* OpenForAppend(const string & filename)
    {
        int pos = filename.rfind("/");
        int outfd = open(filename.substr(pos + 1).c_str(), O_APPEND);
        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;
    }

    virtual ZeroCopyOutputStream* OpenForInsert(const string & filename,
                                        const string & insertion_point)
    {
        int pos = filename.rfind("/");
        int outfd = open(filename.substr(pos + 1).c_str(), O_WRONLY);
        ZeroCopyOutputStream* output = new FileOutputStream(outfd);
        return output;

    }
    virtual void ListParsedFiles(vector< const FileDescriptor * > * output) {}
    virtual void GetCompilerVersion(Version * version) const {}
};


namespace manager {
/*
 * Class that uses Protobuf library to import and generate messages
 * source codes
 */
class VetulusProtoBuilder {

 public:
    explicit VetulusProtoBuilder(const string path)
    {
        this->console = spdlog::get("Proto Loader");
        if (!this->console) {
            this->console = spdlog::stdout_color_mt("Proto Loader");
        }
        this->console->info("Proto Loader");

        if (path.empty()) {
            this->tree.MapPath("vetulus", ".");
        } else {
            this->tree.MapPath("vetulus", path);
        }
        this->importer = new Importer(&tree, &error_collector);
    }

    bool Import(const string file)
    {
        this->file_descriptor = this->importer->Import("vetulus/" + file);
        this->console->info("Importing file: {0}",
                            this->file_descriptor->name());
    }

    bool CppGenerate()
    {
        VetulusContextGenerator context;
        string error;
        CppGenerator generator;

        if (generator.Generate(this->file_descriptor, "", &context, &error)) {
            this->console->info("Probably generated");
            return true;
        }
        this->console->error("Not generated: {0}", error);
        return false;
    }

 private:
    DiskSourceTree tree;
    ErrorCollector error_collector;
    Importer* importer;
    const FileDescriptor* file_descriptor;
    shared_ptr<spdlog::logger> console;
};

};

#endif // _MANAGER_PROTO_LOADER_H
