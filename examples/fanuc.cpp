//
// Created by Imed Rebhi on 10/20/22.
//

#include "fanuc.h"

FanucDPM::FanucDPM(const std::string& host) {
    sessionInfo = std::make_shared<SessionInfo>(host, cipTcpPort, std::chrono::seconds(10));
    messageRouter = std::make_shared<MessageRouter>();
}

std::vector<float> FanucDPM::readPose() {
    auto response = messageRouter->sendRequest(sessionInfo, ServiceCodes::GET_ATTRIBUTE_SINGLE,
                                               EPath(readClassCode, instance, readReg),
                                               {});
    if (!response.getGeneralStatusCode()) {
        Buffer buffer(response.getData());
        CipByte byte1, byte2;
        CipWord word1;
        CipReal x, y, z, w, r, p;
        buffer >> byte1 >> byte2 >> word1 >> x >> y >> z >> w >> r >> p;
        std::cout << "Pose is " << x << " " << y << " " << z << " " << w << " " << r << " " << p << std::endl;
        return std::vector<float>{x, y, z, w, r, p};
    } else {
        std::cout << "We got error=0x" << std::hex << response.getGeneralStatusCode() << std::endl;
        return std::vector<float>{};
    }
}

void FanucDPM::writePose(std::vector<float>& pose) {
    for (int i = 0; i < pose.size(); i++) {
        int16_t signedVal = static_cast<int16_t>(pose[i] * dpmScaleFactor);
        uint16_t unsignedVal;
        if (signedVal < 0)
            unsignedVal = signedVal + 0xFFFF;
        else
            unsignedVal = signedVal;
        std::vector<uint8_t> buffer{static_cast<uint8_t>(unsignedVal), static_cast<uint8_t>(unsignedVal >> 8), 0, 0};
        auto response = messageRouter->sendRequest(sessionInfo, ServiceCodes::SET_ATTRIBUTE_SINGLE,
                                                   EPath(writeClassCode, instance, startWriteReg + i),
                                                   buffer);
        if (!response.getGeneralStatusCode()) {
            std::cout << "Writing is successful" << std::endl;
        } else {
            std::cout << "We got error=0x" << std::hex << response.getGeneralStatusCode() << std::endl;
        }
    }
}
