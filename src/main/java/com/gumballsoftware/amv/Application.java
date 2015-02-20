package com.gumballsoftware.amv;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * Created by ktm on 1/15/15.
 */
@Configuration
@ComponentScan
@EnableAutoConfiguration
public class Application {

    @Bean
    CommandLineRunner init(final ActivitiService as) {
        return new CommandLineRunner() {
            @Override
            public void run(String... strings) throws Exception {
                as.start();
            }
        };
    }

   public static void main(String args[]) {
       SpringApplication.run(Application.class, args);
   }
}

