pipeline {
  agent any
  stages {
    stage('Dependencies') {
      steps {
        sh 'make deps'
      }
    }
    stage('Build') {
      agent any
      environment {
        ARCH = 'x86'
      }
      steps {
        sh 'make all'
      }
    }
  }
  environment {
    ARCH = 'x86'
  }
}