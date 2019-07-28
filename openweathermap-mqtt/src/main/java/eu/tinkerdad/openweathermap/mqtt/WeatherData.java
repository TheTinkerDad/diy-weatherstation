package eu.tinkerdad.openweathermap.mqtt;

import lombok.Data;

@Data
public class WeatherData {

	private Float temp;
	
	private Float humidity;
}
