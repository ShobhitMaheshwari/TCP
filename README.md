mvn archetype:generate

groupId: TCP
artifactId: client/server
version: 1.0-SNAPSHOT
package: Network

java -cp target/server-1.0-SNAPSHOT.jar Network.App
java -cp target/client-1.0-SNAPSHOT.jar Network.App


