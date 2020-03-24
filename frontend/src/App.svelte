<script>
  import Sidebar from './components/sidebar/Sidebar.svelte';
  import Keyboard from './components/keyboard/Keyboard.svelte';
  import Timer from './components/timer/Timer.svelte'

  let connected = false;
  const selectedPortFn = () => connected = true
</script>

<style src="./App.scss"></style>

<div id="app">
  <Sidebar on:selectedPort={selectedPortFn} />

  <main id="main">
    {#if connected}
    <section id="configure" class="animated fadeInRight">
      <div class="card">
        <h1>Configure</h1>
        <Keyboard></Keyboard>
      </div>
    </section>

    <section id="timer" class="animated fadeInRight">
      <div class="card">
        <h1>Timer</h1>
        <Timer></Timer>
      </div>
    </section>
    {/if}


    {#if !connected}
    <section id="notconnected">
      <div class="smallCard">
        Select connected port to access the Dashboard
        <span>😢 😤 🙏</span>
      </div>
    </section>
    {/if}
  </main>
</div>
