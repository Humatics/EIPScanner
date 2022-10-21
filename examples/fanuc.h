//
// Created by Imed Rebhi on 10/20/22.
//

#ifndef FANUC_H
#define FANUC_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "SessionInfo.h"
#include "MessageRouter.h"
#include "ConnectionManager.h"
#include "utils/Buffer.h"

using namespace eipScanner::cip;
using eipScanner::SessionInfo;
using eipScanner::MessageRouter;
using eipScanner::ConnectionManager;
using eipScanner::utils::Buffer;

class FanucDPM {
public:
    explicit FanucDPM(const std::string& host);
    std::vector<float> readPose();
    void writePose(std::vector<float>& pose);

private:
    std::shared_ptr<SessionInfo> sessionInfo;
    std::shared_ptr<MessageRouter> messageRouter;
    const int cipTcpPort = 0xAF12;
    const int dpmScaleFactor = 10;
    const uint16_t readClassCode = 0x7d;
    const uint16_t writeClassCode = 0x6b;
    const uint16_t instance = 1;
    const uint16_t readReg = 1;
    const uint16_t startWriteReg = 601;
};


#endif //FANUC_H
