document.addEventListener('DOMContentLoaded', function () {

  // VARIABLES

  // sections
  var saveX = 0
  var notBoughtYet = true
  const sections = document.getElementsByTagName('section')
  const sectionContainer = document.getElementById('sectionContainer')
  const spontaniousShoppingSection = document.getElementById('spontaniousshopping_section')
  const activateSection = document.getElementById('activate_section')
  var dontScroll = false

  // user
  const user = document.getElementsByClassName('user')

  // basket
  const basket = document.getElementById('basket')

  // navigation
  const navAnchors = document.getElementsByClassName('navAnchor')

  // shopping list
  const list = document.getElementById('list')
  const listItems = list.getElementsByTagName('li')

  // products
  const products = document.getElementsByClassName('buyable')
  const spontaniousProducts = spontaniousShoppingSection.getElementsByClassName('buyable')
  const betterProducts = spontaniousShoppingSection.getElementsByClassName('better')
  const bestProduct = spontaniousShoppingSection.getElementsByClassName('best')
  const sectionsArray = Array.prototype.slice.call(sections)

  // html elements
  const newListItem = document.createElement('li')
  const newListItemContent = document.createTextNode('Kaffee')
  newListItem.appendChild(newListItemContent)
  newListItem.classList.add('bought')

  const moreInformationElements = document.getElementsByClassName('moreInformation')

  // adding Event Listener

  if (sectionContainer.addEventListener) {
    sectionContainer.addEventListener('mousewheel', MouseWheelHandler, false)
    sectionContainer.addEventListener('DOMMouseScroll', MouseWheelHandler, false)
    sectionContainer.addEventListener('touchmove', MouseWheelHandler, false)
  } else sectionContainer.attachEvent('onmousewheel', MouseWheelHandler)

  sectionContainer.addEventListener('scroll', scrollAnimation)

  for (var i = 0; i <= spontaniousProducts.length; i++) {
    if (spontaniousProducts.item(i)) {
      spontaniousProducts.item(i).addEventListener('mouseover', highlightProducts)
      spontaniousProducts.item(i).addEventListener('mouseout', dontHighlightProducts)
    }
  }

  for (var i = 0; i <= sections.length; i++) {
    if (sections[i]) {
      if (i > 0) {
        var moreInformationAnchor = sections[i].getElementsByClassName('sectionInformation')[0].getElementsByTagName('a')[0]
        var hideMoreInformationAnchor = sections[i].getElementsByTagName('a')[0]
        if (moreInformationAnchor) {
          moreInformationAnchor.addEventListener('click', showMoreInformation)
        }
        if (hideMoreInformationAnchor) {
          hideMoreInformationAnchor.addEventListener('click', hideMoreInformation)
        }
      }else {
        var moreInformationAnchor = sections[i].getElementsByClassName('sectionInformation')[0].getElementsByTagName('a')[0]
        var hideMoreInformationAnchor = sections[i].getElementsByTagName('a')[0]
        if (moreInformationAnchor) {
          moreInformationAnchor.addEventListener('click', startShopping)
        }
      }
    }
  }

  document.body.onkeydown = function (e) {
    var code = e.keyCode
    if (code === 39) { // key code for j
      sectionContainer.scrollBy(10, 0)
    }
    else if (code === 37) { // key code for j
      sectionContainer.scrollBy(-10, 0)
    }
  }

  for (var i = 0; i <= products.length; i++) {
    if (products.item(i)) {
      products.item(i).addEventListener('click', buyProduct)
    }
  }

  // functions

  function hideMoreInformation () {
    console.log('ich machs weg')
    let moreInformation = this.parentElement.parentElement.getElementsByClassName('moreInformation')[0]
    console.log(moreInformation)
    moreInformation.classList.remove('visible')
    console.log(moreInformation.classList)
    dontScroll = false
  }

  function showMoreInformation () {
    console.log('ich klicke')
    let moreInformation = this.parentElement.parentElement.getElementsByClassName('moreInformation')[0]
    moreInformation.classList.add('visible')
    console.log(moreInformation.classList)
    dontScroll = true
  }

  function startShopping () {
    sectionContainer.scrollLeft = sections[1].offsetWidth
  }

  function highlightProducts () {
    for (var j = 0; j <= betterProducts.length; j++) {
      if (betterProducts.item(j)) {
        betterProducts.item(j).classList.add('betterProduct')
      }
    }

    if (bestProduct[0]) {
      bestProduct[0].classList.add('bestProduct')
    }
  }

  function dontHighlightProducts () {
    for (var j = 0; j <= betterProducts.length; j++) {
      if (betterProducts.item(j)) {
        betterProducts.item(j).classList.remove('betterProduct')
      }
    }

    if (bestProduct[0]) {
      bestProduct[0].classList.remove('bestProduct')
    }
  }

  function scrollAnimation (event) {
    const scrollPos = sectionContainer.scrollLeft
    const maxScroll = sectionContainer.offsetWidth
    const currentSectionNumber = scrollPos / maxScroll
    const currentSectionIndex = Math.floor(currentSectionNumber)
    // console.log(scrollPos / maxScroll)
    const currentSection = sections[Math.floor(scrollPos / maxScroll)]

    if (currentSectionIndex >= sectionsArray.indexOf(activateSection)) {
      if (basket.classList.contains('fixedBasket')) {
      }
      else
        basket.classList.add('fixedBasket')
    }else {
      basket.classList.remove('fixedBasket')
    }

    for (var i = 0; i <= sections.length; i++) {
      if (currentSectionIndex == i) {
        sections.item(i).classList.add('active')
        navAnchors.item(i).classList.add('active')
      }else if (sections.item(i)) {
        if (sections.item(i).classList.contains('active'))
          sections.item(i).classList.remove('active')
        navAnchors.item(i).classList.remove('active')
      }
    }

    if (currentSection.id == 'home_section') {
      
            list.classList.remove('payed')

      user.item(0).classList.remove('finished')
      user.item(0).classList.remove('pays')

      user.item(0).classList.add('hide')
    }
    else if (currentSection.id == 'start_section') {
            list.classList.remove('payed')

      user.item(0).classList.remove('finished')
      user.item(0).classList.remove('pays')

      user.item(0).classList.remove('hide')
      user.item(0).classList.add('saysHello')
      user.item(0).classList.remove('writesList')
      list.classList.remove('showList')
    }
    else if (currentSection.id == 'list_section') {
            list.classList.remove('payed')

      user.item(0).classList.remove('hide')

      user.item(0).classList.remove('pays')

      user.item(0).classList.remove('finished')

      if (currentSectionNumber > 2.2) {
        list.classList.add('showList')
      }
      user.item(0).classList.remove('activates')
      user.item(0).classList.remove('saysHello')

      list.classList.remove('upperRightList')
      user.item(0).classList.add('writesList')
      user.item(0).classList.remove('saysHello')
    }
    else if (currentSection.id == 'activate_section') {
            user.item(0).classList.remove('saysHello')

            list.classList.remove('payed')

      if (list.classList.contains('showList') == false) {
        list.classList.add('showList')
      }

      user.item(0).classList.remove('hide')

      if (currentSectionNumber < 3.5) {
        user.item(0).classList.add('activates')
      }else {
        user.item(0).classList.remove('activates')
        user.item(0).classList.remove('writesList')
      }
      list.classList.add('upperRightList')
      user.item(0).classList.remove('saysHello')
    }
    else if (currentSection.id == 'checkout_section') {
            user.item(0).classList.remove('saysHello')

      if (list.classList.contains('showList') == false) {
        list.classList.add('showList')
      }
      list.classList.add('payed')
      user.item(0).classList.remove('hide')

      user.item(0).classList.remove('finished')

      if (currentSectionNumber > 6 && currentSectionNumber < 6.3) {
        user.item(0).classList.add('pays')
        console.log('paying')
      }else {
        user.item(0).classList.remove('pays')
      }
    }
    else if (currentSection.id == 'finished_section') {
            user.item(0).classList.remove('saysHello')

      list.classList.add('payed')

      if (list.classList.contains('showList') == false) {
        list.classList.add('showList')
      }
      user.item(0).classList.remove('hide')

      user.item(0).classList.add('finished')
      user.item(0).classList.remove('pays')
    }else {
      if (list.classList.contains('showList') == false) {
        list.classList.add('showList')
      }
      list.classList.remove('payed')

      user.item(0).classList.remove('finished')
      user.item(0).classList.remove('activates')
      user.item(0).classList.remove('writesList')
      user.item(0).classList.remove('pays')

      list.classList.add('upperRightList')
      user.item(0).classList.remove('saysHello')
    }

    if (dontScroll) {
      event.preventDefault()
      console.log('dont scroll')
    }
  }

  function buyProduct () {
    if (this.classList.contains('listproduct')) {
      listItems[0].classList.add('bought')
      this.classList.add('boughtProduct')
    }
    else if (this.classList.contains('spontaniousProduct') && notBoughtYet) {
      this.classList.add('boughtProduct')
      list.appendChild(newListItem)
      notBoughtYet = false
    }
  }

  function MouseWheelHandler (e) {
    if (dontScroll) {
      return
    }
    var e = window.event || e
    var delta = - 20 * (Math.max(-1, Math.min(1, (e.wheelDelta || -e.detail))))

    var pst = sectionContainer.scrollLeft += delta

    if (pst < 0) {
      pst = 0
    } else if (pst > sectionContainer.width) {
      pst = sectionContainer.width
    }

    sectionContainer.scrollLeft = pst

    return false
  }
})
