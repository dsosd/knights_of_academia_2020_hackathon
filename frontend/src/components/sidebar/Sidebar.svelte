<script>
  import {createEventDispatcher} from 'svelte';
  const fire = createEventDispatcher();

  let selectedPort = ''

  const availablePorts = [
    'COM4',
    'COM7',
    'COM10'
  ]

  function selectPort(port) {
    selectedPort = port;
    fire('selectedPort', port)
  }
</script>

<nav>
  <div id="brand">
    <h1>the knights</h1>
  </div>

  <div id="settings">
    <h2 class="label">Settings</h2>
    
    <div id="com">
      <span class="label">Available COM Ports</span>

      <ul id="availPorts">
        {#each availablePorts as port}
          <li>
              <button
                on:click={() => selectPort(port)}
                class:selected={selectedPort === port}
              >{port}</button>
          </li>
        {/each}
      </ul>
    </div>
  </div>
</nav>

<style src="./style.scss"></style>
