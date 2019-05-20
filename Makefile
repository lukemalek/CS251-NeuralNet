OPTS = -Wall -g -std=c++11

GenNetDriver: GenNetDriver.o
	g++ $(OPTS) -o GenNetDriver GenNetDriver.o net_fun.o Neural_net.o  Gen_net.o -lm

GenNetDriver.o: GenNetDriver.cpp Gen_net.o
	g++ $(OPTS) -c GenNetDriver.cpp

Gen_net.o: Neural_net.o Gen_net.cpp Gen_net.h
	g++ $(OPTS) -c Gen_net.cpp

englishTester: englishTester.o
	g++ $(OPTS) -o englishTester englishTester.o net_fun.o Neural_net.o -lm

englishTester.o: englishTester.cpp Neural_net.o
	g++ $(OPTS) -c englishTester.cpp

rspbotvbot: rspbotvbot.o
	g++ $(OPTS) -o rspbotvbot rspbotvbot.o net_fun.o Neural_net.o  RPSBot.o -lm

rspbotvbot.o: rspbotvbot.cpp RPSBot.o
	g++ $(OPTS) -c rspbotvbot.cpp

RPSDriver: RPSDriver.o
	g++ $(OPTS) -o RPSDriver RPSDriver.o net_fun.o Neural_net.o  RPSBot.o -lm

RPSDriver.o: RPSDriver.cpp RPSBot.o
	g++ $(OPTS) -c RPSDriver.cpp

RPSBot.o: Neural_net.o RPSBot.cpp RPSBot.h
	g++ $(OPTS) -c RPSBot.cpp

connect4: connect4.o
	g++ $(OPTS) -o connect4 connect4.o net_fun.o Neural_net.o -lm

connect4.o: connect4.cpp Neural_net.o
	g++ $(OPTS) -c connect4.cpp
	
demo: demo.cpp Neural_net.o 
	g++ $(OPTS) -o demo demo.cpp sd_fun.o str_util.o net_fun.o Neural_net.o -lm

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
	