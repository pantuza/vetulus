
all: server client


server: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ stack_server.cc stack.grpc.pb.cc stack.pb.cc -o stack_server

client: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ stack_client.cc stack.grpc.pb.cc stack.pb.cc -o stack_client

proto: stack.proto
	protoc -I . --cpp_out=. stack.proto

rpc:
	protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=$(shell which grpc_cpp_plugin) stack.proto

clean:
	@rm -v *.pb*
	@rm -v stack_client stack_server
