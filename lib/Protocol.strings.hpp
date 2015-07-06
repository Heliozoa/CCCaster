case MsgType::AckSequence: return ( os << "AckSequence" );
case MsgType::BothInputs: return ( os << "BothInputs" );
case MsgType::ChangeConfig: return ( os << "ChangeConfig" );
case MsgType::ClientMode: return ( os << "ClientMode" );
case MsgType::ConfirmConfig: return ( os << "ConfirmConfig" );
case MsgType::ControllerMappings: return ( os << "ControllerMappings" );
case MsgType::ErrorMessage: return ( os << "ErrorMessage" );
case MsgType::GoBackN: return ( os << "GoBackN" );
case MsgType::InitialConfig: return ( os << "InitialConfig" );
case MsgType::InitialGameState: return ( os << "InitialGameState" );
case MsgType::IpAddrPort: return ( os << "IpAddrPort" );
case MsgType::IpcConnected: return ( os << "IpcConnected" );
case MsgType::JoystickMappings: return ( os << "JoystickMappings" );
case MsgType::JoysticksChanged: return ( os << "JoysticksChanged" );
case MsgType::KeyboardEvent: return ( os << "KeyboardEvent" );
case MsgType::KeyboardMappings: return ( os << "KeyboardMappings" );
case MsgType::MenuIndex: return ( os << "MenuIndex" );
case MsgType::NetplayConfig: return ( os << "NetplayConfig" );
case MsgType::OptionsMessage: return ( os << "OptionsMessage" );
case MsgType::PaletteManager: return ( os << "PaletteManager" );
case MsgType::Ping: return ( os << "Ping" );
case MsgType::PingStats: return ( os << "PingStats" );
case MsgType::PlayerInputs: return ( os << "PlayerInputs" );
case MsgType::RngState: return ( os << "RngState" );
case MsgType::SocketShareData: return ( os << "SocketShareData" );
case MsgType::SpectateConfig: return ( os << "SpectateConfig" );
case MsgType::SplitMessage: return ( os << "SplitMessage" );
case MsgType::Statistics: return ( os << "Statistics" );
case MsgType::SyncHash: return ( os << "SyncHash" );
case MsgType::TestMessage: return ( os << "TestMessage" );
case MsgType::TransitionIndex: return ( os << "TransitionIndex" );
case MsgType::UdpControl: return ( os << "UdpControl" );
case MsgType::Version: return ( os << "Version" );
case MsgType::VersionConfig: return ( os << "VersionConfig" );
