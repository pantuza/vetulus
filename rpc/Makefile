
all: server client


server: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ server.cc stack.grpc.pb.cc stack.pb.cc -o server

client: proto rpc
	g++ -std=c++11 -lprotobuf -lgrpc++ client.cc stack.grpc.pb.cc stack.pb.cc -o client

proto: stack.proto
	protoc -I . --cpp_out=. stack.proto

rpc:
	protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=$(shell which grpc_cpp_plugin) stack.proto

clean:
	@rm -v *.pb*
	@rm -v client server
