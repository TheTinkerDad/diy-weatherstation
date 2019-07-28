package eu.tinkerdad.openweathermap.mqtt;

import org.springframework.core.convert.converter.Converter;
import org.springframework.stereotype.Component;

import eu.tinkerdad.openweathermap.mqtt.api.WeatherResponse;

@Component
public class WeatherConverter implements Converter<WeatherResponse, WeatherData> {

	@Override
	public WeatherData convert(WeatherResponse input) {

		WeatherData data = new WeatherData();
		data.setTemp(input.getList().get(0).getMain().getTemp());
		data.setHumidity(input.getList().get(0).getMain().getHumidity());
		return data;
	}

}
