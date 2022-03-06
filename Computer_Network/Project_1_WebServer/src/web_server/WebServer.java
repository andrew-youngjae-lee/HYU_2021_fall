package web_server;

import java.util.*;
import java.net.*;
import java.io.*;

public class WebServer {

	public static void main(String[] args) {
		try {
			ServerSocket serverSock = new ServerSocket(9290); // *mission 1
			while (true) {
				Socket connectionSock = serverSock.accept();
				HttpRequest request = new HttpRequest(connectionSock);
				Thread thread = new Thread(request); // *mission 2
				thread.start();						
			}
		}
		catch (IOException e) {
			System.out.println(e.getMessage());
		}catch(Exception e) {
			System.out.println(e.getMessage());
		}

	}

}
