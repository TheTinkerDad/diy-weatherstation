package eu.tinkerdad.openweathermap.mqtt;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;

import lombok.extern.slf4j.Slf4j;

@Slf4j
@Configuration
@EnableScheduling
public class Scheduler {

	@Value("${weatherstation.temperature.topic}")
	private String tTopic;

	@Value("${weatherstation.humidity.topic}")
	private String hTopic;
	
	@Autowired
	private WeatherUpdater weather;
	
	@Autowired
	private MqttPublisher mqtt;
	
	@Scheduled(fixedDelay = 60000)
	public void sendUpdate() {
		log.info("Triggering OpenWeatherMap API call...");
		
		try {
			weather.update();
			mqtt.publish(tTopic, String.format("%.2f", weather.get().getTemp()));
			mqtt.publish(hTopic, String.format("%.2f", weather.get().getHumidity()));
		} catch (Exception e) {
			log.error("Failed to update weather data!", e);
		}
	}
}
