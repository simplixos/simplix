pipeline {
  agent any
  stages {
    stage('Dependencies') {
      steps {
        sh 'make deps'
      }
    }
    stage('Build') {
      steps {
        sh 'make'
      }
    }
  }
  environment {
    ARCH = 'x86'
  }
}