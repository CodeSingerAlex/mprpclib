#include "friend.pb.h"
#include "mprpcapplication.h"
#include <iostream>

int main(int argc, char **argv) {
  MprpcApplication::Init(argc, argv);

  fixbug::FiendServiceRpc_Stub stub(new MprpcChannel());
  fixbug::GetFriendsListRequest request;
  request.set_userid(1000);
  fixbug::GetFriendsListResponse response;
  MprpcController controller;
  stub.GetFriendsList(&controller, &request, &response, nullptr);

  if (controller.Failed()) {
    std::cout << controller.ErrorText() << std::endl;
  } else {
    if (0 == response.result().errcode()) {
      std::cout << "rpc GetFriendsList response success!" << std::endl;
      int size = response.friends_size();
      for (int i = 0; i < size; ++i) {
        std::cout << "index:" << (i + 1) << " name:" << response.friends(i)
                  << std::endl;
      }
    } else {
      std::cout << "rpc GetFriendsList response error : "
                << response.result().errmsg() << std::endl;
    }
  }

  return 0;
}
