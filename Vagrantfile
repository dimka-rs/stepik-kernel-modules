# -*- mode: ruby -*-
# vi: set ft=ruby :

kvm_support = system("/usr/sbin/kvm-ok > /dev/null")

Vagrant.configure(2) do |config|
  config.ssh.guest_port = 22
  config.ssh.username = 'vagrant'
  config.ssh.password = 'vagrant'
  config.vm.define "kernel" do |domain|
    domain.vm.box = "osll_moocs/jessie64_with_kernel_headers"
  end
  config.vm.provider "libvirt" do |libvirt|
    libvirt.graphics_type = "vnc"
    libvirt.graphics_port = "5901"
    ##libvirt.management_network_mac = "0800271dfee1"
     if kvm_support then
      libvirt.driver = "kvm"
    else
      libvirt.driver = "qemu"
    end
  end
end
