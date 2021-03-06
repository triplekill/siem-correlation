/**
 *   @file   IReceiveServer.h
 *   @brief  brief
 *
 *   detail
 *
 *   @internal www.captech.net.cn
 *   author:    Zhang peng
 *   mail:      zhangpeng@captech.net.cn,Developer.Zhang.Peng@gmail.com
 *   Created:   Nov 17, 2014
 *   Revision:  1.0.0
 *   Compiler:  gcc/g++
 *   Company:   Captech Co., Ltd.
 *   Copyright: Copyright (c) 2008, Captech Co., Ltd.
 *
 * =====================================================================================
 */

#ifndef IRECEIVESERVER_H_
#define IRECEIVESERVER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <pthread.h>

#include "SIEMEventBuild.h"

namespace SIEM
{

class IReceiveServer : public boost::noncopyable
{
public:
    IReceiveServer()
    :m_pthServerID(0),
     m_ptrSIEMBuild(new CSIEMEventBuild())
    {
    }
    virtual ~IReceiveServer(){}
public:
    bool virtual Start()         = 0;
    bool virtual Initialize()    = 0;
public:
    inline bool Stop();
    inline bool Join();
protected:
    pthread_t                           m_pthServerID;
    boost::shared_ptr<CSIEMEventBuild>  m_ptrSIEMBuild;
};

inline bool IReceiveServer::Join()
{
    void *pRet;
    if(pthread_join(m_pthServerID, &pRet))
    {
        return false;
    }
    return true;
}

inline bool IReceiveServer::Stop()
{
    if(pthread_cancel(m_pthServerID))
    {
        return false;
    }
    return true;
}

} /* namespace SIEM */
#endif /* IRECEIVESERVER_H_ */
