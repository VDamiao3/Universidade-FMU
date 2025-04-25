document.addEventListener("DOMContentLoaded", function () {
  const carousel = document.querySelector(".carousel");
  const slides = document.querySelectorAll(".carousel-slide");
  const dots = document.querySelectorAll(".dot");

  let currentIndex = 0;
  const slideCount = slides.length;
  let startX, moveX;
  let isDragging = false;

  // Função para mover o carrossel
  function moveCarousel(index) {
    if (index < 0) {
      currentIndex = slideCount - 1;
    } else if (index >= slideCount) {
      currentIndex = 0;
    } else {
      currentIndex = index;
    }

    carousel.style.transform = `translateX(-${currentIndex * 100}%)`;
    updateDots();
  }

  // Atualizar os indicadores de pontos
  function updateDots() {
    dots.forEach((dot, index) => {
      if (index === currentIndex) {
        dot.classList.add("active");
      } else {
        dot.classList.remove("active");
      }
    });
  }

  // Adicionar eventos aos pontos
  dots.forEach((dot) => {
    dot.addEventListener("click", function () {
      const slideIndex = parseInt(this.getAttribute("data-index"));
      moveCarousel(slideIndex);
    });
  });

  // Suporte a touch/swipe para navegação
  carousel.addEventListener("touchstart", function (e) {
    startX = e.touches[0].clientX;
    isDragging = true;
  });

  carousel.addEventListener("touchmove", function (e) {
    if (!isDragging) return;
    moveX = e.touches[0].clientX;
  });

  carousel.addEventListener("touchend", function () {
    if (!isDragging) return;

    const diffX = startX - moveX;
    if (diffX > 50) {
      // Swipe para esquerda
      moveCarousel(currentIndex + 1);
    } else if (diffX < -50) {
      // Swipe para direita
      moveCarousel(currentIndex - 1);
    }

    isDragging = false;
  });

  // Iniciar autoslide
  let autoSlide = setInterval(() => {
    moveCarousel(currentIndex + 1);
  }, 5000);

  // Pausar o autoslide quando o mouse está sobre o carrossel
  carousel.addEventListener("mouseenter", () => {
    clearInterval(autoSlide);
  });

  carousel.addEventListener("mouseleave", () => {
    autoSlide = setInterval(() => {
      moveCarousel(currentIndex + 1);
    }, 5000);
  });
});
