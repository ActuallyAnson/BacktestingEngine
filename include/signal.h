#pragma once

enum class Signal {
    Buy,
    Hold,
    Sell,
};

inline const char* signalToString (Signal signal) {
    switch(signal) {
        case Signal::Buy: return "BUY";
        case Signal::Hold: return "HOLD";
        case Signal::Sell: return "SELL";
        default: return "UNKNOWN";
    }
}
