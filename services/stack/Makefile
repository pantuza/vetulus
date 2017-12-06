PROTOS_DIR := ../../protos

all: server client


server: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ stack_server.cc stack.grpc.pb.cc stack.pb.cc dog.pb.cc -o stack_server

client: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ stack_client.cc stack.grpc.pb.cc stack.pb.cc dog.pb.cc -o stack_client

proto: $(PROTOS_DIR)/stack.proto $(PROTOS_DIR)/dog.proto
	protoc -I $(PROTOS_DIR) --cpp_out=. dog.proto stack.proto

rpc:
	protoc -I $(PROTOS_DIR) --grpc_out=. --plugin=protoc-gen-grpc=$(shell which grpc_cpp_plugin) stack.proto

clean:
	@rm -v *.pb*
	@rm -v stack_client stack_server
