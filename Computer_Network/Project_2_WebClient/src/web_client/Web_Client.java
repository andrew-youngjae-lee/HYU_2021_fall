package web_client;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

import javax.xml.transform.Templates;

public class Web_Client {

	public static String getWebContentByGet(String urlString,String agent, final String charset, int timeout) throws IOException {
		if (urlString == null || urlString.length() == 0) {
			return null;
		}
		urlString = (urlString.startsWith("http://") || urlString.startsWith("https://")) ? urlString
				: ("http://" + urlString).intern();
		URL url = new URL(urlString);
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setRequestMethod("GET");
		conn.setRequestProperty("User-Agent",
				agent);
		conn.setRequestProperty("Accept", "text/html");
		conn.setConnectTimeout(timeout);
		try {
			if (conn.getResponseCode() != HttpURLConnection.HTTP_OK) {
				return null;
			}
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
		InputStream input = conn.getInputStream();
		BufferedReader reader = new BufferedReader(new InputStreamReader(input, charset));
		String line = null;
		StringBuffer sb = new StringBuffer();
		while ((line = reader.readLine()) != null) {
			sb.append(line).append("\r\n");
		}
		if (reader != null) {
			reader.close();
		}
		if (conn != null) {
			conn.disconnect();
		}
		return sb.toString();
	}

	public static String getWebContentByPost(String urlString, String agent,String data, final String charset, int timeout)
			throws IOException {
		if (urlString == null || urlString.length() == 0) {
			return null;
		}
		urlString = (urlString.startsWith("http://") || urlString.startsWith("http://")) ? urlString
				: ("http://" + urlString).intern();
		URL url = new URL(urlString);
		HttpURLConnection connection = (HttpURLConnection) url.openConnection();

		connection.setDoOutput(true);
		connection.setDoInput(true);
		connection.setRequestMethod("POST");
		connection.setUseCaches(false);
		connection.setInstanceFollowRedirects(true);
		connection.setRequestProperty("Connection-Type", "text/xml;charset=UTF-8");
		connection.setRequestProperty("User-Agent", agent);
		connection.setRequestProperty("Accept", "text/xml");
		connection.setConnectTimeout(timeout);
		connection.connect();
		DataOutputStream out = new DataOutputStream(connection.getOutputStream());

		byte[] content = data.getBytes("UTF-8");

		out.write(content);
		out.flush();
		out.close();
		try {
			if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
				return null;
			}
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
		BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream(),charset));
		String line;
		StringBuffer sb = new StringBuffer();
		while ((line = reader.readLine()) != null) {
			sb.append(line).append("\r\n");
		}
		if (reader != null) {
			reader.close();
		}
		if (connection != null) {
			connection.disconnect();
		}
		return sb.toString();
	}
	
	
	public static void main(String [] args) {
	      Scanner sc = new Scanner(System.in);
	      String url,agent,data,temp;
	      try {
	         while(true) {
	        	System.out.println("Input Command");
	            temp = sc.next();
	            if(temp.equals("GET")) {
	            	System.out.println("What kind of file you want to GET ?");
	            	String mode;
	            	mode = sc.next();
	            	if(mode.equals("text")) {
	            		System.out.println("Input URL");
	 	               url = sc.next();
	 	               agent = "2017003027/YoungJae+Lee/WEBCLIENT/COMPUTERNETWORK";
	 	               String response;
	 	               response = Web_Client.getWebContentByGet(url,agent,"UTF-8", 10000);
	 	            
	 	               System.out.println(response);
	            	}
	            	else if (mode.equals("image")) {
	            		System.out.println("Input URL");
		 	            url = sc.next();
		 	            agent = "2017003027/YoungJae+Lee/WEBCLIENT/COMPUTERNETWORK";
		 	            ImageGUI image = new ImageGUI();
		 	            image.imshow(url);
	            	}
	               
	            }
	            else if(temp.equals("POST")) {
	               System.out.println("Input URL");
	               url = sc.next();
	      
	               
	               agent = "2017003027/YoungJae+Lee/WEBCLIENT/COMPUTERNETWORK";
	               System.out.println("Input Data");
	               data = sc.next();
	               String response = Web_Client.getWebContentByPost(url,agent, "2017003027/"  + data, "UTF-8", 10000);
	               System.out.println(response);
	            }
	            
	            else break;
	         }
	      } catch (IOException e) {
	         e.printStackTrace();
	      }
	}
}
