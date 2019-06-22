document.addEventListener('DOMContentLoaded', function () {

  // VARIABLES

  // sections
  const sections = document.getElementsByTagName('section')
  const sectionContainer = document.getElementById('sectionContainer')
  const spontaniousShoppingSection = document.getElementById('spontaniousshopping_section')
  const activateSection = document.getElementById('activate_section')

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

  // adding Event Listener
  if (sectionContainer.addEventListener) {
    sectionContainer.addEventListener('mousewheel', MouseWheelHandler, false)
    sectionContainer.addEventListener('DOMMouseScroll', MouseWheelHandler, false)
  } else sectionContainer.attachEvent('onmousewheel', MouseWheelHandler)

  sectionContainer.addEventListener('scroll', scrollAnimation)

  for (var i = 0; i <= spontaniousProducts.length; i++) {
    if (spontaniousProducts.item(i)) {
      spontaniousProducts.item(i).addEventListener('mouseover', highlightProducts)
      spontaniousProducts.item(i).addEventListener('mouseout', dontHighlightProducts)
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

  function scrollAnimation () {
    const scrollPos = sectionContainer.scrollLeft
    const maxScroll = sectionContainer.offsetWidth
    const currentSectionIndex = Math.floor((scrollPos / maxScroll))
    console.log(scrollPos / maxScroll)
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

    if (currentSection.id == 'activate_section') {
      user.item(0).classList.add('activates')
      list.classList.add('upperRightList')
    }
    else if (currentSection.id == 'list_section') {
      user.item(0).classList.remove('activates')
      list.classList.remove('upperRightList')

      user.item(0).classList.add('writesList')
    }
    else if (currentSection.id == 'start_section' || currentSection.id == 'home_section') {
      user.item(0).classList.add('writesList')
    }else {
      user.item(0).classList.remove('activates')
      user.item(0).classList.remove('writesList')
    }
  }

  function buyProduct () {
    if (this.classList.contains('listproduct')) {
      listItems[0].classList.add('bought')
      this.classList.add('boughtProduct')
    }
    else if (this.classList.contains('spontaniousProduct') && listItems.length < 2) {
      this.classList.add('boughtProduct')
      list.appendChild(newListItem)
    }
  }


  function MouseWheelHandler (e) {
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
