#pragma once

#include <QMap>
#include <QString>
#include "hal_core/defines.h"

namespace hal {

    class NetlistSimulator;
    class Net;

    class WaveData : public QMap<int,int>
    {
        u32 mId;
        QString mName;
    public:
        WaveData(u32 id_, const QString& nam, const QMap<int,int>& other = QMap<int,int>() );
        WaveData(const Net* n);
        u32 id() const { return mId; }
        QString name() const { return mName; }
        int tValue(float t) const;
        void setStartvalue(int val);
        bool insertToggleTime(int t);
        QString textValue(const QMap<int,int>::const_iterator& it) const;
        static WaveData* clockFactory(Net* n, int start, int period, int duration);
        static WaveData* simulationResultFactory(Net* n, const NetlistSimulator* sim);
    };
}
