// if (screen.width < 450) {
//     alert('Less than 450')
// change to mobil view 
// }
// else {

//     alert('More than 450')
// }
document.addEventListener('DOMContentLoaded', function () {
  var subtopics = document.getElementsByClassName('subtopic')

  for (var i = 0; i < subtopics.length; i++) {
    subtopics[i].addEventListener('mouseover', highlightSame)
  }

  function highlightSame () {
    let same = []
    let topic
    for(var i = 0; i < this.classList.length; i++){
            if(this.classList[i] != "subtopic" && this.classList[i] != "highlighted"){
                    topic = this.classList[i]
            }
    }

    console.log(topic)

    for(var i = 0; i < subtopics.length; i++){
            subtopics[i].classList.remove("highlighted")
            if(subtopics[i].classList.contains(topic) && subtopics[i] != this){
                    console.log(subtopics[i])
                    subtopics[i].classList.add("highlighted")
            }
    }
  }
})
