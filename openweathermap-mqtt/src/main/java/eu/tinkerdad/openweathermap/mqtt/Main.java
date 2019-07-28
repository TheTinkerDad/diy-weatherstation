package eu.tinkerdad.openweathermap.mqtt;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
@EnableScheduling
@ComponentScan
public class Main {

	@Bean
	public RestTemplate restTemplate() {
		return new RestTemplate();
	}
	
    public static void main(String[] args) {
        SpringApplication.run(Main.class, args);
    }
}
