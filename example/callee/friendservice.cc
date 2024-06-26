#include "friend.pb.h"
#include "logger.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <iostream>
#include <string>
#include <vector>

class FriendService : public fixbug::FiendServiceRpc {
public:
  std::vector<std::string> GetFriendsList(uint32_t userid) {
    std::cout << "do GetFriendsList service! userid:" << userid << std::endl;
    std::vector<std::string> vec;
    vec.push_back("gao yang");
    vec.push_back("liu hong");
    vec.push_back("wang shuo");
    return vec;
  }

  // 重写基类方法
  void GetFriendsList(::google::protobuf::RpcController *controller,
                      const ::fixbug::GetFriendsListRequest *request,
                      ::fixbug::GetFriendsListResponse *response,
                      ::google::protobuf::Closure *done) {
    uint32_t userid = request->userid();
    std::vector<std::string> friendsList = GetFriendsList(userid);
    response->mutable_result()->set_errcode(0);
    response->mutable_result()->set_errmsg("");
    for (std::string &name : friendsList) {
      std::string *p = response->add_friends();
      *p = name;
    }
    done->Run();
  }
};

int main(int argc, char **argv) {
  LOG_ERR("ddddd");
  LOG_INFO("ddddd");

  MprpcApplication::Init(argc, argv);

  RpcProvider provider;
  provider.NotifyService(new FriendService());

  provider.Run();

  return 0;
}
