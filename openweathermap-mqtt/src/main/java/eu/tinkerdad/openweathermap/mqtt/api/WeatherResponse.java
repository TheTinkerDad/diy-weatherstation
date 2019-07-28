package eu.tinkerdad.openweathermap.mqtt.api;

import java.util.ArrayList;
import java.util.List;

import lombok.Getter;
import lombok.ToString;

@ToString
public class WeatherResponse {

	@Getter
	private List<WeatherResponseListItem> list = new ArrayList<>();
}
