package eu.tinkerdad.openweathermap.mqtt.api;

import lombok.Data;
import lombok.ToString;

@Data
@ToString
public class WeatherResponseListItem {

	private SensorData main;
}
