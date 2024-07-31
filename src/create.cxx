auto plugin::create(plugin::Host host) -> plugin::Plugin {
    return plugin::make<ExamplePlugin>(host);
}
