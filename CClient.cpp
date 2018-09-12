/**************************************************************************
* Author: 	Ajish KB
**************************************************************************/

#include "Client.h"
#include <string>

using namespace std;

bool CClient::MbSentDataToTsd(vector<MbDataPacket> dataVector, string BatchId)
{
    TSDStreaming::MbDataTransfer dataTransfer;
    TSDStreaming::MbDatRecvResponse dataResponse;
    ClientContext context;

    dataTransfer.set_batchid(BatchId);

    for(int idx = 0 ; idx < dataVector.size(); idx++)
    {
        TSDStreaming::MbDataPacket* dataPacket = dataTransfer.add_mb_packet();
        string Str = dataVector[idx].mb_asset_id();
        dataPacket->set_mb_asset_id(Str);
        dataPacket->set_mb_status(dataVector[idx].mb_status());
        dataPacket->set_mb_value(dataVector[idx].mb_value());
        dataPacket->set_mb_tag_type(dataVector[idx].mb_tag_type());
        dataPacket->set_mb_unit(dataVector[idx].mb_unit());
        dataPacket->set_mb_time(dataVector[idx].mb_time());
    }

    Status status = stub_->MbSentDataToTsd(&context, dataTransfer, &dataResponse);

    if (status.ok())
    {
      return true;
    }
    else
    {
      return false;
    }

}
