#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "figure.h"
#include "point.h"
#include "factory.h"
#include "hexagon.h"
#include "pentagon.h"
#include "octagon.h"
#include "subscriber.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "To check test_01.txt put in ./lab8 3 < test_01.txt";
        return 0;
    }
	unsigned int BufSize = std::atoi(argv[1]);
	std::vector<std::shared_ptr<figure>> f;
	std::string cmd;
	factory factory;
	bool done = false;
	std::condition_variable rd;
	std::condition_variable hd;
	std::mutex mutex;
	int in = 1;
	std::vector<std::shared_ptr<sub>> s;
	s.push_back(std::make_shared<ConsolePrint>());
	s.push_back(std::make_shared<FilePrint>());
	std::thread sub([&]() {
		std::unique_lock<std::mutex> sub_lock(mutex);
		while (!done) {
			rd.wait(sub_lock);
			if (done) {
				hd.notify_all();
				break;
			}
			for (unsigned int i = 0; i < s.size(); i ++) {
				s[i]->Print(f);

			}
			in++;
			f.resize(0);
			hd.notify_all();
		}
	});

	std::cout << "1 - to add " << BufSize << " figures\n"
        		 "2 - to finish execution of program\n";
	while(cmd != "2") {

        std::cin >> cmd;
        if (cmd != "2") {
            std::unique_lock<std::mutex> main_lock(mutex);
            for (unsigned int i = 0; i < BufSize; i++) {
                f.push_back(factory.FigureCreate(std::cin));
                if (f.size() == BufSize) {
        			std::cout << "Buffer is full!\n";
        		}
            }
            rd.notify_all();
            hd.wait(main_lock);
        }
    }
    done = true;
    rd.notify_all();
    sub.join();
    return 0;

}
