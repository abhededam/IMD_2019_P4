document.addEventListener('DOMContentLoaded', function () {
  const sectionContainer = document.getElementById('sectionContainer')
  const sections = document.getElementsByTagName('section')
  const sectionsArray = Array.prototype.slice.call(sections)
  const wagen_s = document.getElementById('wagen_section')
  const warenkorb = document.getElementById('warenkorb')

  sectionContainer.addEventListener('scroll', scrollAnimation)

  function scrollAnimation () {
    console.log('scrolling')
    const scrollPos = sectionContainer.scrollLeft
    const maxScroll = sectionContainer.offsetWidth*1.5
    const currentSectionIndex = Math.floor((scrollPos / maxScroll))
    console.log(scrollPos / maxScroll)
    const currentSection = sections[Math.floor(scrollPos / maxScroll)]
    if (currentSectionIndex >= sectionsArray.indexOf(wagen_s)) {
      if (warenkorb.classList.contains('fixedWarenkorb')) {
      }
      else
        warenkorb.classList.add('fixedWarenkorb')
    }
    else{
        warenkorb.classList.remove('fixedWarenkorb')
    }

    for (var i = 0; i <= sectionsArray.length; i++) {
      if (currentSectionIndex == i) {
        sections.item(i).classList.add('active')
      }else {
        if (sections.item(i).classList.contains('active'))
          sections.item(i).classList.remove('active')
      }
    }
  }













if (sectionContainer.addEventListener) {
    sectionContainer.addEventListener("mousewheel", MouseWheelHandler, false);
    sectionContainer.addEventListener("DOMMouseScroll", MouseWheelHandler, false);
} else sectionContainer.attachEvent("onmousewheel", MouseWheelHandler);

function MouseWheelHandler(e) {

    // cross-browser wheel delta
    var e = window.event || e;
    var delta = - 20 * (Math.max(-1, Math.min(1, (e.wheelDelta || -e.detail))));

    var pst = sectionContainer.scrollLeft += delta;

    if (pst < 0) {
        pst = 0;
    } else if (pst > sectionContainer.width()) {
        pst = sectionContainer.width();
    }

    sectionContainer.scrollLeft = pst;

    return false;
}



  
})
