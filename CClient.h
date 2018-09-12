/**************************************************************************
* Author: 	Ajish KB
**************************************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>
#include <vector>
#include <grpc++/grpc++.h>

#include "proto_stub/SxDataTransfer.grpc.pb.h"
#include "proto_stub/SxDataTransfer.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using TSDStreaming::MbDataTransfer;
using TSDStreaming::MbDataPacket;
using namespace grpc;
using namespace std;

class CClient
{
public:
 CClient(std::shared_ptr<Channel> channel):stub_(TSDStreaming::DataTransfer::NewStub(channel)) {}

 bool MbSentDataToTsd(std::vector<MbDataPacket>, string);

private:
 std::unique_ptr<TSDStreaming::DataTransfer::Stub> stub_;

};

#endif // CLIENT_H
