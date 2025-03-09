#include "music.h"
#include <windows.h>
#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

namespace ducktimer{
    void music::play() const{
        CoInitialize(nullptr);
    
        IGraphBuilder* pGraph = nullptr;
        IMediaControl* pControl = nullptr;
        IMediaEvent* pEvent = nullptr;
    
        // 创建 Filter Graph
        CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
        pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
        pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    
        // 加载 MP3 文件
        pGraph->RenderFile(filename, nullptr);
    
        // 开始播放
        pControl->Run();
    
        // 等待播放结束
        long evCode;
        pEvent->WaitForCompletion(INFINITE, &evCode);
    
        // 释放资源
        pControl->Release();
        pEvent->Release();
        pGraph->Release();
        CoUninitialize();
    
    }
};