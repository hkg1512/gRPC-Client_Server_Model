/**************************************************************************
* Author: 	Ajish KB
**************************************************************************/

#include "Server.h"
#include "Client.h"
#include <grpc++/grpc++.h>
#include <string>
#include <vector>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace std;

void RunServer(string AddrStr)
{
    ServerImpl service;
    ServerBuilder builder;

    builder.AddListeningPort(AddrStr, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << AddrStr << std::endl;

    server->Wait();
}

int main(int argc, char *argv[])
{
    if(argc == 4)
    {
        string Ip = argv[2];
        string Port = argv[3];
        string Addr = Ip+":"+Port;

        if(!strcmp(argv[1],"Server"))
        {
            RunServer(Addr);
        }
        else if(!strcmp(argv[1],"Client"))
        {
            CClient client(grpc::CreateChannel(Addr, grpc::InsecureChannelCredentials()));
            TSDStreaming::MbDataPacket dataPacket;
            vector<TSDStreaming::MbDataPacket>dataVector;
            string Prompt("NO");
            int idy = 0;

            do
            {
                for(int idx = 0; idx < 4; idx++)
                {
                    string Str("test" +to_string(idx));

                    dataPacket.set_mb_asset_id(Str);
                    dataPacket.set_mb_status(Str);
                    dataPacket.set_mb_tag_type(Str);
                    dataPacket.set_mb_time(Str);
                    dataPacket.set_mb_unit(Str);
                    dataPacket.set_mb_value(Str);

                    dataVector.push_back(dataPacket);
                }

                string BatchId(to_string(idy));

                client.MbSentDataToTsd(dataVector,BatchId);
                dataVector.clear();
                idy++;

                cerr << endl<<"\t\tSend again???: ";
                cin  >> Prompt;
            }
            while(Prompt == "YES" || Prompt == "yes");
        }
        else
        {
            cerr << "\nUnknown arguments";
        }
    }

    return 0;
}
