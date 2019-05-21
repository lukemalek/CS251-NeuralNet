OPTS = -Wall -g -std=c++11

connect4driver: connect4driver.o
	g++ $(OPTS) -o connect4driver connect4driver.o net_fun.o Neural_net.o connect4.o -lm

connect4driver.o: connect4driver.cpp connect4.o
	g++ $(OPTS) -c connect4driver.cpp

connect4.o: net_fun.o connect4.h connect4.cpp
	g++ $(OPTS) -c connect4.cpp

connect4total: connect4total.o
	g++ $(OPTS) -o connect4total connect4total.o net_fun.o Neural_net.o -lm

connect4total.o: connect4total.cpp Neural_net.o net_fun.o
	g++ $(OPTS) -c connect4total.cpp

englishLearner: englishLearner.o
	g++ $(OPTS) -o englishLearner englishLearner.o net_fun.o Neural_net.o -lm

englishLearner.o: englishLearner.cpp Neural_net.o
	g++ $(OPTS) -c englishLearner.cpp

NetDriver: NetDriver.o
	g++ $(OPTS) -o NetDriver NetDriver.o net_fun.o Neural_net.o -lm

NetDriver.o: NetDriver.cpp Neural_net.o
	g++ $(OPTS) -c NetDriver.cpp

Neural_net.o: net_fun.o Neural_net.h Neural_net.cpp
	g++ $(OPTS) -c Neural_net.cpp

functionDriver: functionDriver.o
	g++ $(OPTS) -o functionDriver functionDriver.o net_fun.o -lm

functionDriver.o: functionDriver.cpp net_fun.o
	g++ $(OPTS) -c functionDriver.cpp

net_fun.o: net_fun.h net_fun.cpp
	g++ $(OPTS) -c net_fun.cpp
	