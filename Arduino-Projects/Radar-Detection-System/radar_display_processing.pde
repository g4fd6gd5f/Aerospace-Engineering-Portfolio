import processing.serial.*;

Serial myPort;

String data = "";
int angle = 0;
int distance = 0;

void setup() {
  size(1200, 700);
  smooth();

  // Your Arduino is on COM5
  myPort = new Serial(this, "COM5", 9600);
  myPort.bufferUntil('.');
}

void draw() {
  fill(0, 4);
  noStroke();
  rect(0, 0, width, height);

  drawRadar();
  drawLine();
  drawText();
}

void serialEvent(Serial myPort) {
  data = myPort.readStringUntil('.');

  if (data != null) {
    data = trim(data);

    if (data.length() > 1) {
      data = data.substring(0, data.length() - 1);

      int commaIndex = data.indexOf(",");

      if (commaIndex > 0) {
        angle = int(data.substring(0, commaIndex));
        distance = int(data.substring(commaIndex + 1));
      }
    }
  }
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height - 70);

  stroke(0, 255, 0);
  strokeWeight(2);
  noFill();

  // Distance arcs
  arc(0, 0, 900, 900, PI, TWO_PI);
  arc(0, 0, 700, 700, PI, TWO_PI);
  arc(0, 0, 500, 500, PI, TWO_PI);
  arc(0, 0, 300, 300, PI, TWO_PI);

  // Base line
  line(-450, 0, 450, 0);

  // Angle lines
  for (int a = 30; a <= 150; a += 30) {
    float x = 450 * cos(radians(a));
    float y = -450 * sin(radians(a));
    line(0, 0, x, y);
  }

  popMatrix();
}

void drawLine() {
  pushMatrix();
  translate(width / 2, height - 70);

  // Green when clear, red when object is detected
  if (distance < 40) {
    stroke(255, 0, 0);
    strokeWeight(7);
  } else {
    stroke(0, 255, 0);
    strokeWeight(4);
  }

  float x = 450 * cos(radians(angle));
  float y = -450 * sin(radians(angle));

  line(0, 0, x, y);

  popMatrix();
}

void drawText() {
  fill(0);
  noStroke();
  rect(0, height - 60, width, 60);

  fill(0, 255, 0);
  textSize(24);

  text("Angle: " + angle + "°", 40, height - 25);

  if (distance < 40) {
    fill(255, 0, 0);
    text("Distance: " + distance + " cm", 250, height - 25);
    text("Object detected", 520, height - 25);
  } else {
    fill(0, 255, 0);
    text("Distance: Out of range", 250, height - 25);
    text("No object detected", 520, height - 25);
  }
}
