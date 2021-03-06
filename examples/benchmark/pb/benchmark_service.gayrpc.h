// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef DODO_BENCHMARK_BENCHMARK_SERVICE_H
#define DODO_BENCHMARK_BENCHMARK_SERVICE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>
#include <chrono>

#include <google/protobuf/util/json_util.h>

#include "meta.pb.h"
#include "benchmark_service.pb.h"

#include "GayRpcCore.h"
#include "GayRpcError.h"
#include "GayRpcTypeHandler.h"
#include "GayRpcClient.h"
#include "GayRpcService.h"
#include "GayRpcReply.h"

namespace dodo {
namespace benchmark {

    using namespace gayrpc::core;
    using namespace google::protobuf::util;
    
    enum class benchmark_service_ServiceID:uint32_t
    {
        EchoServer,
        
    };

    
    enum class EchoServerMsgID:uint64_t
    {
        Echo = 2333,
        
    };

    class EchoServerClient : public BaseClient
    {
    public:
        typedef std::shared_ptr<EchoServerClient> PTR;
        typedef std::weak_ptr<EchoServerClient> WeakPtr;

        typedef std::function<void(const dodo::benchmark::EchoResponse&,
            const gayrpc::core::RpcError&)> EchoHandle;
        

    public:
        void Echo(const dodo::benchmark::EchoRequest& request,
            const EchoHandle& handle = nullptr)
        {
            call<dodo::benchmark::EchoResponse>(request, 
                static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle);
        }
        
        void Echo(const dodo::benchmark::EchoRequest& request,
            const EchoHandle& handle,
            std::chrono::seconds timeout, 
            BaseClient::TIMEOUT_CALLBACK timeoutCallback)
        {
            call<dodo::benchmark::EchoResponse>(request, 
                static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle,
                timeout,
                std::move(timeoutCallback));
        }
        

        dodo::benchmark::EchoResponse SyncEcho(
            const dodo::benchmark::EchoRequest& request,
            gayrpc::core::RpcError& error)
        {
                auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
                auto responsePromise = std::make_shared<std::promise<dodo::benchmark::EchoResponse>>();

                Echo(request, [responsePromise, errorPromise](const dodo::benchmark::EchoResponse& response,
                    const gayrpc::core::RpcError& error) {
                    errorPromise->set_value(error);
                    responsePromise->set_value(response);
                });

                error = errorPromise->get_future().get();
                return responsePromise->get_future().get();
        }
        

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& outboundInterceptor,
            const UnaryServerInterceptor& inboundInterceptor)
        {
            struct make_shared_enabler : public EchoServerClient
            {
            public:
                make_shared_enabler(const UnaryServerInterceptor& outboundInterceptor,
                    const UnaryServerInterceptor& inboundInterceptor)
                    : 
                    EchoServerClient(outboundInterceptor, inboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(outboundInterceptor, inboundInterceptor));
            client->installResponseStub(rpcHandlerManager, static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer));

            return client;
        }

    private:
        using BaseClient::BaseClient;
    };

    class EchoServerService : public BaseService
    {
    public:
        typedef std::shared_ptr<EchoServerService> PTR;
        typedef std::weak_ptr<EchoServerService> WeakPtr;

        typedef TemplateReply<dodo::benchmark::EchoResponse> EchoReply;
        

        virtual ~EchoServerService()
        {
        }

        virtual void onClose() {}

        static inline bool Install(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor);
    private:
        virtual void Echo(const dodo::benchmark::EchoRequest& request, 
            const EchoReply::PTR& replyObj) = 0;
        

    private:

        static void Echo_stub(const RpcMeta& meta,
            const std::string& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            dodo::benchmark::EchoRequest request;
            
            switch (meta.encoding())
            {
            case RpcMeta::BINARY:
                if (!request.ParseFromString(data))
                {
                    throw std::runtime_error("parse binary Echo error");
                }
                break;
            case RpcMeta::JSON:
                {
                    auto s = JsonStringToMessage(data, &request);
                    if (!s.ok())
                    {
                        throw std::runtime_error("parse json Echo failed:" +
                            s.error_message().as_string());
                    }
                }
                break;
            default:
                throw std::runtime_error("parse Echo of unsupported encoding type:" + meta.encoding());
            }

            inboundInterceptor(meta,
                request,
                [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message) {
                auto replyObject = std::make_shared<EchoReply>(meta, outboundInterceptor);
                service->Echo(request, replyObject);
            });
        }
        
    };

    inline bool EchoServerService::Install(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
        const EchoServerService::PTR& service,
        const UnaryServerInterceptor& inboundInterceptor,
        const UnaryServerInterceptor& outboundInterceptor)
    {
        typedef std::function<void(const RpcMeta&,
            const std::string& data,
            const EchoServerService::PTR&,
            const UnaryServerInterceptor&,
            const UnaryServerInterceptor&)> EchoServerServiceRequestHandler;

        typedef std::unordered_map<uint64_t, EchoServerServiceRequestHandler> EchoServerServiceHandlerMapById;
        typedef std::unordered_map<std::string, EchoServerServiceRequestHandler> EchoServerServiceHandlerMapByStr;

        // TODO::static unordered map
        auto serviceHandlerMapById = std::make_shared<EchoServerServiceHandlerMapById>();
        auto serviceHandlerMapByStr = std::make_shared<EchoServerServiceHandlerMapByStr>();

        std::string namespaceStr = "dodo.benchmark.";

        (*serviceHandlerMapById)[static_cast<uint64_t>(EchoServerMsgID::Echo)] = EchoServerService::Echo_stub;
        
        (*serviceHandlerMapByStr)[namespaceStr+"EchoServer.Echo"] = EchoServerService::Echo_stub;
        

        auto requestStub = [service,
            serviceHandlerMapById,
            serviceHandlerMapByStr,
            inboundInterceptor,
            outboundInterceptor](const RpcMeta& meta, const std::string& data) {
            
            if (meta.type() != RpcMeta::REQUEST)
            {
                throw std::runtime_error("meta type not request, It is:" + std::to_string(meta.type()));
            }
            
            EchoServerServiceRequestHandler handler;

            if (!meta.request_info().strmethod().empty())
            {
                auto it = serviceHandlerMapByStr->find(meta.request_info().strmethod());
                if (it == serviceHandlerMapByStr->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().strmethod());
                }
                handler = (*it).second;
            }
            else
            {
                auto it = serviceHandlerMapById->find(meta.request_info().intmethod());
                if (it == serviceHandlerMapById->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().intmethod());
                }
                handler = (*it).second;
            }

            handler(meta,
                data,
                service,
                inboundInterceptor,
                outboundInterceptor);
        };

        return rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub, static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer));
    }
    
}
}

#endif

