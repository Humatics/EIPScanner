//
// Created by Imed Rebhi on 10/20/22.
//

#include "fanuc.h"

int main() {
    auto fanuc = FanucDPM("192.168.29.246");
    auto pose = fanuc.readPose();
    pose[0] /= 2;
    fanuc.writePose(pose);
    return 0;
}
