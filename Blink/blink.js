/* jslint esversion: 6  */
let context = new p5();

let vol1 = 0;
let vol2 = 0;
let vol3 = 0;
let vol4 = 0;

let time = 0;


function preload() {
    soundFormats('mp3');
    lamp1 = loadSound('./Lampe1.mp3');
    lamp2 = loadSound('./Lampe2.mp3');
    lamp3 = loadSound('./Lampe3.mp3');
    lamp4 = loadSound('./Lampe4.mp3');

    
    picture = loadImage("./hintergrund.png");

    lamp1pic = loadImage("./lamp1.png");
    lamp2pic = loadImage("./lamp2.png");
    lamp3pic = loadImage("./lamp3.png");
    lamp4pic = loadImage("./lamp4.png");
   
}

function setup(){ 
    createCanvas(windowWidth, windowHeight);
    frameRate(60);

    lamp1.loop();
    lamp2.loop();
    lamp3.loop();
    lamp4.loop();

    lamp1.setVolume(0);
    lamp2.setVolume(0);
    lamp3.setVolume(0);
    lamp4.setVolume(0); 
    
}

function draw(){
    createCanvas(windowWidth, windowHeight);
    clear();
    time +=1;
    if(time > 135 ){
        time = 0;
    }
    image(picture,0,0,windowWidth, windowHeight);

    if(time<15){
        image(lamp1pic,0,0,windowWidth, windowHeight);
        image(lamp4pic,0,0,windowWidth, windowHeight);
    }
    if(time>=15&&time<30){
        image(lamp1pic,0,0,windowWidth, windowHeight);
        image(lamp2pic,0,0,windowWidth, windowHeight);
        image(lamp4pic,0,0,windowWidth, windowHeight);
    }
    if(time>=30&&time<45){
        image(lamp1pic,0,0,windowWidth, windowHeight);
        image(lamp2pic,0,0,windowWidth, windowHeight);
    }
    if(time>=45&&time<60){
        image(lamp1pic,0,0,windowWidth, windowHeight);
    }
    if(time>=60&&time<75){
        image(lamp2pic,0,0,windowWidth, windowHeight);
        image(lamp3pic,0,0,windowWidth, windowHeight);
        image(lamp4pic,0,0,windowWidth, windowHeight);
    }
    if(time>=70&&time<90){
        image(lamp2pic,0,0,windowWidth, windowHeight);
        image(lamp3pic,0,0,windowWidth, windowHeight);
        image(lamp4pic,0,0,windowWidth, windowHeight);
    }
    if(time>=90&&time<105){
        image(lamp1pic,0,0,windowWidth, windowHeight);
        image(lamp2pic,0,0,windowWidth, windowHeight);
        image(lamp4pic,0,0,windowWidth, windowHeight);
    }
    if(time>=105&&time<120){
        image(lamp1pic,0,0,windowWidth, windowHeight);
        image(lamp2pic,0,0,windowWidth, windowHeight);
        image(lamp3pic,0,0,windowWidth, windowHeight);
    }
    if(time>=120&&time<=135){
        image(lamp3pic,0,0,windowWidth, windowHeight);
    }
    
    
    
    
    
    if(vol1==1){
        fill(0);
        rect(windowWidth/1.14,windowHeight/3,50,50);
        lamp1.setVolume(0.1);
        vol2=0;
        vol3=0;
        vol4=0;
    }
    else{
        noFill();
        rect(windowWidth/1.14,windowHeight/3,50,50);
        lamp1.setVolume(0);
        
    }

    if(vol2==1){
        fill(0);
        rect(windowWidth/18,windowHeight/1.5,50,50);
        lamp2.setVolume(0.1);
        vol1=0;
        vol3=0;
        vol4=0;
    }
    else{
        noFill();
        rect(windowWidth/18,windowHeight/1.5,50,50);
        lamp2.setVolume(0);
    }

    if(vol3==1){
        fill(0);
        rect(windowWidth/1.14,windowHeight/1.5,50,50);
        lamp3.setVolume(0.1);
        vol2=0;
        vol1=0;
        vol4=0;
    }
    else{
        noFill();
        rect(windowWidth/1.14,windowHeight/1.5,50,50);
        lamp3.setVolume(0);
    }

    if(vol4==1){
        fill(0);
        rect(windowWidth/18,windowHeight/3,50,50);
        lamp4.setVolume(0.1); 
        vol2=0;
        vol3=0;
        vol1=0;
    }
    else{
        noFill();
        rect(windowWidth/18,windowHeight/3,50,50);
        lamp4.setVolume(0);
    }     
    
}

function mouseClicked(){
    if(mouseX>windowWidth/1.14&&mouseX<windowWidth/1.14+50&&mouseY>windowHeight/3&&mouseY<windowHeight/3+50){
        if(vol1==1){
            vol1=0;
        }
        else{
            vol1=1;
        
        }
        
        
    }
    else if(mouseX>windowWidth/18&&mouseX<windowWidth/18+50&&mouseY>windowHeight/1.5&&mouseY<windowHeight/1.5+50){
        if(vol2==1){
            vol2=0;
        }
        else{
            vol2=1;
        }
    }
    else if(mouseX>windowWidth/18&&mouseX<windowWidth/18+50&&mouseY>windowHeight/3&&mouseY<windowHeight/3+50){
        
        if(vol4==1){
            vol4=0;
        }
        else{
            vol4=1;
        }
    }
    else if(mouseX>windowWidth/1.14&&mouseX<windowWidth/1.14+50&&mouseY>windowHeight/1.5&&mouseY<windowHeight/1.5+50){
        
        if(vol3==1){
            vol3=0;
        }
        else{
            vol3=1;
        }
    }
}
