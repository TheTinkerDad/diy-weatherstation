package eu.tinkerdad.openweathermap.mqtt;

import java.net.ConnectException;

import javax.annotation.PostConstruct;

import org.fusesource.mqtt.client.BlockingConnection;
import org.fusesource.mqtt.client.MQTT;
import org.fusesource.mqtt.client.QoS;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import lombok.extern.slf4j.Slf4j;

@Slf4j
@Component
public class MqttPublisher {

	@Value("${mqtt.host}")
	private String mqttHost;

	@Value("${mqtt.port}")
	private String mqttPort;
	
	@Value("${mqtt.user}")
	private String mqttUser;

	@Value("${mqtt.pass}")
	private String mqttPass;
	
	private MQTT mqtt;
	
	@PostConstruct
	public void init() throws Exception {
		
		log.info("Initializing MQTT connection...");
		
    	mqtt = new MQTT();
    	mqtt.setHost(mqttHost, Integer.parseInt(mqttPort));
    	mqtt.setUserName(mqttUser);
    	mqtt.setPassword(mqttPass);
	}
	
	public void publish(String topic, String message) throws Exception {
		
    	BlockingConnection connection = mqtt.blockingConnection();
    	connection.connect();
    	if (connection.isConnected()) {
    		log.info("Publishing data: T=" + topic + ", M=" + message);
	    	connection.publish(topic, message.getBytes(), QoS.AT_LEAST_ONCE, false);
	    	connection.disconnect();
    	} else {
    		throw new ConnectException("Failed to connect to MQTT broker!");
    	}	
	}
}
