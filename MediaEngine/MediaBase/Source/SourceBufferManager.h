/*
* This software is developed for study and improve coding skill ...
*
* Project:  Enjoyable Coding< EC >
* Copyright (C) 2014-2016 Gao Peng

* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.

* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.

* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the Free
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

* ---------------------------------------------------------------------
* SourceBufferManager.h
* This file defines the source buffer manager, management of the source
* buffer, read the video/audio/subtitle stream and store them to this
* buffer manager, then the decoder will get these buffers via framework.
*
* Eamil:   epengao@126.com
* Author:  Peter Gao
* Version: Intial first version.
* --------------------------------------------------------------------
*/

#ifndef SOURCE_BUFFER_MANAGER_H
#define SOURCE_BUFFER_MANAGER_H

#include "ECType.h"
#include "Source.h"
#include "ECThread.h"
#include "ECRingQueue.h"
#include "ECMsgHandler.h"
#include "FFmpegReader.h"

#define SOURCE_BUFFER_QUEUE_MAX_SIZE 256

class SourceBufferManager
{
public:
    SourceBufferManager(EC_U32 nBufferQueueMaxSize = SOURCE_BUFFER_QUEUE_MAX_SIZE);
    ~SourceBufferManager();

    EC_BOOL IsVideoBufferQueueFull();
    EC_BOOL IsAudioBufferQueueFull();

    /* Video Buffer Property*/
    EC_U32 PushVideoBuffer(SourceBuffer *pBuffer);
    EC_U32 PopVideoBuffer(SourceBuffer **pBuffer);
    EC_U32 PushReuseVideoBuffer(SourceBuffer *pBuffer);
    EC_U32 PopReuseVideoBuffer(SourceBuffer **pBuffer);
    /* Audio Buffer Property*/
    EC_U32 PushAudioBuffer(SourceBuffer *pBuffer);
    EC_U32 PopAudioBuffer(SourceBuffer **pBuffer);
    EC_U32 PushReuseAudioBuffer(SourceBuffer *pBuffer);
    EC_U32 PopReuseAudioBuffer(SourceBuffer **pBuffer);

private:
    /* Video Buffer Queue */
    ECMutex                     m_mtxVideoBuf;
    ECRingQueue<SourceBuffer*>* m_pVideoBufQueue;
    /* Audio Buffer Queue */
    ECMutex                     m_mtxAudioBuf;
    ECRingQueue<SourceBuffer*>* m_pAudioBufQueue;
    /* Audio & Video Reuse Buf Queue */
    ECMutex                     m_mtxAVReuseBuf;
    ECRingQueue<SourceBuffer*>* m_pReuseAVBufQueue;
};

#endif /* SOURCE_BUFFER_MANAGER_H */