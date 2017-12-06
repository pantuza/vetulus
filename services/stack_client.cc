
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::ostringstream;
using std::thread;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using StackService::StackServer;
using StackService::Item;
using StackService::Empty;

class StackClient {
 public:
    StackClient(std::shared_ptr<Channel> channel)
    : stub_(StackServer::NewStub(channel))
    {}

    bool Push(Item item) {
        ClientContext context;
        Empty reply;

        Status status = this->stub_->Push(&context, item, &reply);
        if (status.ok()) {
            return true;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
        }

        return false;
    }

    Item* Pop() {
        ClientContext context;
        Empty none;
        Item* item = new Item();

        Status status = this->stub_->Pop(&context, none, item);

        if (status.ok()) {
            return item;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
        }
        return NULL;
    }

 private:
    std::unique_ptr<StackServer::Stub> stub_;
};


int main(int argc, char* argv[]) {


    cout << "gRPC Stack Server example" << endl;
//    cout << "Enter a name to Push() on the stack. "
//         << "Press Enter to Pop() from the stack" << endl << endl;


    for (int i = 0; i < 100; i++) {

        thread* th = new thread([=] {
            StackClient client(grpc::CreateChannel(
                "localhost:50051", grpc::InsecureChannelCredentials()));
            Item item;
            ostringstream ostr;
            ostr << "Item " << i;
            item.set_name(ostr.str());
            cout << "Push(" << item.name() << ")" << endl;
            client.Push(item);
        });

        th->detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

//    string name;
//    while (true) {
//        cout << "Name: ";
//        getline(cin, name);
//        if (name.size() > 0) {
//            item.set_name(name);
//            client.Push(item);
//            cout << "Push(" << item.name() << ")" << endl;
//        } else {
//            item = *client.Pop();
//            cout << "Pop(" << item.name() << ")" << endl;
//        }
//    }
//
    return EXIT_SUCCESS;
}
