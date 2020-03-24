<script>
  let minutes = '00';
  let seconds = '00';
  let percentage = '0';

  // time in seconds
  function startTimer(time) {
    let timeElapsed = 0;

    const loop = setInterval(() => {
      const timeLeft = time - timeElapsed;
      if (timeElapsed === time) {
        percentage = 0;
        clearInterval(loop);
      }

      timeElapsed += 1;
    
      let tempMinutes = Math.floor(timeLeft / 60);
      minutes = tempMinutes < 10 ? `0${tempMinutes}` : tempMinutes
      let tempSeconds = timeLeft % 60;
      seconds = tempSeconds < 10 ? `0${tempSeconds}` : tempSeconds
      percentage = ((timeElapsed / time) * 100).toString();
    }, 1000)
  }

  // TODO: Expose to parent startTimer fn
</script>

<div id="timer">
  <div id="time">
    {minutes} : {seconds}
    <span>
      {minutes} : {seconds}
    </span>
  </div>

  <span class="tip">Use the knob on your keyboard to set and start timer</span>
</div>

<style src='./style.scss'></style>
