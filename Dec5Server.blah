import java.io.*;
import java.net.*;
/***********************************************
* A basic server that receives message from clients.
* Messages are echoed back to the client.
* @author Gloire Rubambiza
* @date 09/24/2016
***********************************************/

public class Server  {
  /*****************************************
   Hanles all incoming client requests
   ****************************************/
  public static void main (String [] args) throws IOException{

    try {
    // Reads user input for the port of the server
    BufferedReader inFromUser =
    new BufferedReader(
    new InputStreamReader(System.in));
    System.out.println("Please specify a port");
    int port = Integer.parseInt(inFromUser.readLine());

    // Checks user input for correct port number
    while(1024 > port || port > 9999){
      System.out.println("Please enter a valid port");
      port = Integer.parseInt(inFromUser.readLine());
    }

    // Open a server socket for connection over the specified port
    final ServerSocket serverSocket = new ServerSocket(port);

    // Accepts a client connection
    final Socket clientSocket = serverSocket.accept();
    System.out.println("A client connection has been established");

    //Sends file to the client
    PrintStream outToClient =
    new PrintStream(
    clientSocket.getOutputStream());

    // Receives file specification from client
    BufferedReader inFromClient =
    new BufferedReader(
    new InputStreamReader(
    clientSocket.getInputStream()));
    String clientMessage = inFromClient.readLine();
    System.out.println("Request for " + clientMessage +
    " file received" + '\n');


      // Find the specified file and send it to client
      File n = new File(clientMessage);
      FileInputStream clientrequest = new FileInputStream(clientMessage);
      long filesize = n.length();
      outToClient.println((int)filesize);
      byte[] buffer = new byte[1024*16];

      // Write and sending the file
      while(clientrequest.read(buffer) > 0){
        outToClient.write(buffer);
      }

      clientrequest.close();
      outToClient.close();
    }
    //Notify the client if there was an error reading the file
    catch (FileNotFoundException e){
      e.printStackTrace();
      //outToClient.writeBytes("File not found");
      //System.out.println("File not found!");
      System.exit(0);
    }

  }
}
