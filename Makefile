all: main

main: main.cpp common.h machine_list.pb.h machine_list.pb.cc
	g++ main.cpp machine_list.pb.cc -o main -lprotobuf -pthread

machine_list.pb.h: machine_list.proto
	protoc --cpp_out=. machine_list.proto

machine_list.pb.cc: machine_list.proto

tests: tests.cpp common.h machine_list.pb.h machine_list.pb.cc
	g++ tests.cpp machine_list.pb.cc -o tests -lprotobuf -pthread -lgtest

clean:
	rm machine_list.pb.h machine_list.pb.cc main tests
