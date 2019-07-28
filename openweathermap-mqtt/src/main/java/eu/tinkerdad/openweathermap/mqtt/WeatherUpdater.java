package eu.tinkerdad.openweathermap.mqtt;

import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;

import javax.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.convert.ConversionService;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestClientException;
import org.springframework.web.client.RestTemplate;

import eu.tinkerdad.openweathermap.mqtt.api.WeatherResponse;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@Component
public class WeatherUpdater {

	@Value("${openweathermap.host}")
	private String host;

	@Value("${openweathermap.port}")
	private String port;

	@Value("${openweathermap.endpoint}")
	private String endpoint;
	
	@Value("${openweathermap.token}")
	private String token;

	@Value("${openweathermap.location}")
	private String location;
	
	@Autowired
	private RestTemplate restTemplate;

	@Autowired
	private ConversionService converter;
	
	private String url;
	
	private WeatherData currentData;
	
	@PostConstruct
	public void init() {
		
		url = new StringBuilder()
		.append(host)
		.append(":")
		.append(port)
		.append(endpoint)
		.append("?q=")
		.append(location)
		.append("&appid=")
		.append(token)
		.append("&cnt=1&units=metric")
		.toString();
	}
	
	public void update() throws Exception {

		HttpHeaders headers = new HttpHeaders();
		headers.setContentType(MediaType.APPLICATION_JSON);
    	
		ResponseEntity<WeatherResponse> response = restTemplate.getForEntity(new URI(url), WeatherResponse.class);
		currentData = converter.convert(response.getBody(), WeatherData.class);
	}
	
	public WeatherData get() {
		return currentData;
	}

}
