mvn archetype:generate

groupId: TCP
artifactId: client/server
version: 1.0-SNAPSHOT
package: Network


mvn compile
mvn package
java -cp target/server-1.0-SNAPSHOT.jar Network.App
java -cp target/client-1.0-SNAPSHOT.jar Network.App


make server
make client
./clientout localhost 4547

./serverout 4547

Testing server
to check that server is listening on correct port/ip
netstat -apn | egrep "serverout"

To check if server is correctly responding
netcat localhost 4547
telnet localhost 4547

Both above will block for input from stdin - So give a message and server will recieve the message
