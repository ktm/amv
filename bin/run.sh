#!/bin/sh

java -cp target/classes:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activation-1.1.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-bpmn-converter-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-bpmn-model-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-engine-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-image-generator-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-process-validation-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/activiti-spring-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/aopalliance-1.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/commons-dbcp-1.4.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/commons-email-1.2.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/commons-lang3-3.3.2.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/commons-logging-1.1.3.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/commons-pool-1.6.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/h2-1.4.184.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jackson-annotations-2.4.4.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jackson-core-2.4.4.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jackson-databind-2.4.4.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jcl-over-slf4j-1.7.10.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/joda-time-2.5.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jssc-2.8.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/jul-to-slf4j-1.7.10.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/log4j-over-slf4j-1.7.10.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/logback-classic-1.1.2.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/logback-core-1.1.2.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/mail-1.4.1.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/mybatis-3.2.5.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/slf4j-api-1.7.10.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/snakeyml-1.14.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-aop-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-beans-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-autoconfigure-1.2.2.BUILD-SNAPSHOT.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-1.2.2.BUILD-SNAPSHOT.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-starter-1.2.2.BUILD-SNAPSHOT.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-starter-basic-5.17.0.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-starter-jdbc-1.2.2.BUILD-SNAPSHOT.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-boot-starter-logging-1.2.2.BUILD-SNAPSHOT.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-context-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-core-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-expression-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-jdbc-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-orm-4.1.4.RELEASE.jar:\
target/AMV-0.0.1-SNAPSHOT/WEB-INF/lib/spring-tx-4.1.4.RELEASE.jar \
com.gumballsoftware.amv.AMVApplication




