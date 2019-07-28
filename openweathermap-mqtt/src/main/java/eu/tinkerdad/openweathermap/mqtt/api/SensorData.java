package eu.tinkerdad.openweathermap.mqtt.api;

import lombok.Data;
import lombok.ToString;

@Data
@ToString
public class SensorData {

	private Float temp;
	
	private Float humidity;
}
