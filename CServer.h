/**************************************************************************
* Author: 	Ajish KB
**************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <grpc++/grpc++.h>

#include "proto_stub/SxDataTransfer.grpc.pb.h"
#include "proto_stub/SxDataTransfer.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using TSDStreaming::MbDataTransfer;
using TSDStreaming::MbDataPacket;
using TSDStreaming::DataTransfer;
using namespace std;

class ServerImpl: public DataTransfer::Service
{
    Status MbSentDataToTsd(::grpc::ServerContext* context, const ::TSDStreaming::MbDataTransfer* request, ::TSDStreaming::MbDatRecvResponse* response)
            override
    {
        cerr <<endl <<endl<<endl << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
        cerr << "BATCHID: " << request->batchid() << endl;
        cerr << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
        for(int idx = 0; idx < request->mb_packet_size(); idx++)
        {
            cerr << "DATA PACKET - "+to_string(idx) << endl;
            cerr << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
            cerr << "AssetId: " << request->mb_packet(idx).mb_asset_id()<<endl;
            cerr << "Unit: " <<request->mb_packet(idx).mb_unit()<<endl;
            cerr << "Value: " << request->mb_packet(idx).mb_value()<<endl;
            cerr << "Status: " << request->mb_packet(idx).mb_status()<<endl;
            cerr << "Time: " << request->mb_packet(idx).mb_time()<<endl;
            cerr << "Tag_Type: "<< request->mb_packet(idx).mb_tag_type()<<endl;
            cerr << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
        }

        return Status::OK;
    }
};

#endif // SERVER_H
