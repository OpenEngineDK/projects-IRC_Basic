// main
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/IEngine.h>
#include <Core/Engine.h>
#include <Core/IListener.h>
#include <Core/EngineEvents.h>

#include <Logging/ILogger.h>
#include <Logging/Logger.h>
#include <Logging/ColorStreamLogger.h>

#include <Network/IRCClient.h>
#include <Network/IRCChannel.h>

using namespace OpenEngine::Core;
using namespace OpenEngine::Network;
using namespace OpenEngine::Logging;

class ActionHandler : public IListener<ProcessEventArg>,
                      public IListener<JoinedChannelArg>,
                      public IListener<MessageEventArg>
{
    IRCChannel* channel;
    bool channelSet;
public:
    
    ActionHandler()
        : channel(0)
    {
    }

    void Handle(JoinedChannelArg arg)
    {
        channel = arg.channel;
        (channel->ChannelMessageEvent()).Attach(*this);
    }
    
    void Handle(ProcessEventArg arg)
    {
        if(channel)
        {
        //    channel->SendMsg("TEST MESSAGE");
        }
    }

    void Handle(MessageEventArg arg)
    {
        if(arg.channel==channel)
        {
            logger.info << arg.user << ">>" << arg.message << logger.end;
        }
    }
};

int main(int argc, char** argv)
{
    //INIT STUFF
    IEngine* engine = new Engine();

    ILogger* stdlog = new ColorStreamLogger(&std::cout);
    Logger::AddLogger(stdlog);

    //IRC CLIENT
    IRCClient client("irc.freenode.org", "OE_BOT", "OE_BOT");
    client.Join("#openengine");
    engine->ProcessEvent().Attach(client);
    engine->DeinitializeEvent().Attach(client);
    client.Start();

    ActionHandler act;
    client.JoinedChannelEvent().Attach(act);
    engine->ProcessEvent().Attach(act);

    //Start it
    engine->Start();
    
    return 0;
}
