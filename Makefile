all: main

main: main.cpp equipment.h machine_list.pb.h machine_list.pb.cc
	g++ main.cpp machine_list.pb.cc -o main -lprotobuf

machine_list.pb.h: machine_list.proto
	protoc --cpp_out=. machine_list.proto

machine_list.pb.cc: machine_list.proto
	noop

clean:
	rm machine_list.pb.h machine_list.pb.cc main
