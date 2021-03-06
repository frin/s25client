// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.
#ifndef iwDIRECTIPCONNECT_H_INCLUDED
#define iwDIRECTIPCONNECT_H_INCLUDED

#pragma once

#include "ClientInterface.h"
#include "IngameWindow.h"
#include "gameTypes/ServerType.h"

class iwDirectIPConnect : public IngameWindow, public ClientInterface
{
private:
    ServerType server_type;

public:
    iwDirectIPConnect(ServerType server_type);
    void SetHost(const std::string& host);
    void SetPort(unsigned short port);
    /// Connects to the given server or fills in the info if it has a password
    void Connect(const std::string& hostOrIp, const unsigned short port, const bool isIPv6, const bool hasPwd);

private:
    void SetText(const std::string& text, unsigned color, bool button);

    void Msg_EditChange(const unsigned ctrl_id) override;
    void Msg_EditEnter(const unsigned ctrl_id) override;
    void Msg_ButtonClick(const unsigned ctrl_id) override;
    void Msg_OptionGroupChange(const unsigned ctrl_id, const int selection) override;

    void CI_Error(const ClientError ce) override;
    void CI_NextConnectState(const ConnectState cs) override;
};

#endif // !iwDIRECTIPCONNECT_H_INCLUDED
